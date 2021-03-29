//
// Created by Kirill on 3/13/2021.
//

#include <cstring>
#include "Text.h"
#include "TTextFactory.h"

void TText::set_root(TTextNode *r) {
    this->root = r;
}

TText::TText(TTextNode *r) {
    this->root = r;
}

TTextNode *TText::get_root() {
    return this->root;
}

TText::iterator TText::begin() {
    return TText::iterator(this->root);
}

TText::iterator TText::find(char c) {
    TTextIterator iter = this->begin();
    while(iter.get()){
        if(*(iter.get()) == c)
            break;
        iter.go_next_char();
    }
    return iter;
}

TText::iterator TText::find(char *s) {
    TTextIterator iter = this->begin();
    bool not_found = true;
    int str_index = 0;
    int found_length = strlen(s);
    while(iter.get() && not_found){
        if(*(iter.get()) == s[str_index]){
            TTextIterator iter2 = iter;
            while(iter2.get()){
                if(*(iter2.get()) == s[str_index]){
                    str_index++;
                    iter2.go_next_char();
                    if(str_index == found_length){
                        not_found = false;
                        break;
                    }
                }else{
                    str_index = 0;
                    break;
                }
            }
        }else{
            str_index = 0;
            iter.go_next_char();
        }
    }
    if(not_found){
        iter.reset();
    }
    return iter;
}

TText::iterator TText::find(NodeLevel level, char *s) {
    if(level == NodeLevel::LETTER){
        return this->find(s[0]);
    }
    TTextNode* node = TTextFactory::create_node(s, level);
    TTextIterator iter = this->begin();
    iter.reset_to(level);
    while(iter.get()){
        if(*(iter.get()) == *(node)){
            break;
        }
        iter.go_next(level);
    }
    return iter;
}

TText::~TText() {
    TStack<TTextNode*> stack;
    while(!this->root->is_letter()){
        stack.push(this->root);
        this->root = this->root->get_down();
    }
    TTextNode* prev_letter= nullptr;
    while(this->root != nullptr){
        prev_letter = this->root;
        this->root = this->root->get_next();
        delete prev_letter;
    }
    while(!stack.is_empty()){
        TTextNode* prev_level = stack.pop();
        TTextNode* prev_level_delete = prev_level;
        if(prev_level->has_next()) {
            prev_level = prev_level->get_next();
            delete prev_level_delete;
            while (!prev_level->is_letter()) {
                stack.push(prev_level);
                prev_level = prev_level->get_down();
            }
            prev_letter= nullptr;
            while(prev_level != nullptr){
                prev_letter = prev_level;
                prev_level = prev_level->get_next();
                delete prev_letter;
            }
        }else{
            delete prev_level_delete;
        }
    }
    this->root = nullptr;
}

TText::iterator TText::insert(char *s, TText::iterator in) {
    if(in.get()){
        TTextNode* node = TTextFactory::create_node(s, in.get()->get_level());
        TTextNode* next = in.get()->get_next();
        node->set_next(next);
        in.get()->set_next(node);
    }
    return in;
}

TText::iterator TText::_delete(int to_delete, TText::iterator i) {
    int deleted = 0;
    TStack<TTextNode *> deleting(1000);
    TTextNode **prevs = new TTextNode *[5];
    bool void_structure = false;
    while (deleted < to_delete) {
        renew_prevs(i, prevs);
        TTextNode *current = i.get();
        if (current->get_next() == nullptr) {
            // у буквы нет следующей
            TTextIterator next_elem_to_delete = i;
            next_elem_to_delete.go_next();
            int level = 0;
            // ресет на уровень выше (буква-слово и тд)
            while (level < 5) {
                auto higher_level = static_cast<NodeLevel>(static_cast<int>(level) + 1);
                i.reset_to(higher_level);
                TTextNode *word = i.get();
                if (current) {
                    if (current->get_level() == NodeLevel::LETTER) deleted++;
                    deleting.push(current);
                    if (&(*(word->get_down())) == &(*current) && !current->has_next()) {
                        // если удаляемый обьект был корневым и не имеет следующего
                        void_structure = true;
                    }
                }

                if (!void_structure) {
                    // структура удалена не полностью
                    i = next_elem_to_delete;
                    break;
                } else {
                    // у структуры нету down, значит в нем все було удалено, надо перекинуть prev и удалить само слово
                    if (word->has_next()) {
                        // стрктура вложенная но не последняя
                        int higher_level_int = static_cast<int>(higher_level);
                        // в превсах может быть только на один уровень выше, так что устанавливаем вниз
                        if (prevs[higher_level_int] == nullptr) {
                            this->root = word->get_next();
                        } else if (prevs[higher_level_int]->get_level() != higher_level) {
                            prevs[higher_level_int]->set_down(word->get_next());
                        } else {
                            prevs[higher_level_int]->set_next(word->get_next());
                        }
                        i = next_elem_to_delete;
                        break;
                    } else {
                        // структура последняя
                        // подьем выше - цикл
                        current = word;
                        level++;
                    }
                    void_structure = false;
                }
            }

        } else {
            // у буквы есть следующая буква
            // в превсах может быть только на один уровень выше, так что устанавливаем вниз
            if (prevs[0]->get_level() != NodeLevel::LETTER) {
                prevs[0]->set_down(current->get_next());
            } else {
                prevs[0]->set_next(current->get_next());
            }
            i.go_next();
            deleting.push(current);
            deleted++;
        }
    }
    delete[] prevs;
    return i;
}

void TText::renew_prevs(TTextIterator &i, TTextNode **&prevs) {
    NodeLevel level = i.get()->get_level();
    if (level != NodeLevel::LETTER) {
        i.go_next_char();
    }
    // количество уровней
    for (int k = 0; k < 5; ++k) {
        TTextIterator j = i;
        TTextIterator q = i;
        j.reset_to(static_cast<NodeLevel>(k + 1));
        q.reset_to(static_cast<NodeLevel>(k));
        if (j.get() == nullptr) {
            // такое возможно если мы на самом верхнем уровне, и нету у него старшего NodeLevel::TEXT
            prevs[k] = j.get();
            break;
        }
        // проверить не является ли i rootом
        j.go_next();
        if (&(*j.get()) == &(*q.get())) {
            j.reset_to(static_cast<NodeLevel>(k + 1));
            prevs[k] = j.get();
            //prev нет (точнее сказать предыдущий для этой структуры будет структура уровня выше)
        } else {
            // prev есть
            while (j.get()) {
                if (&(*(j.get()->get_next())) == &(*(q.get()))) {
                    break;
                }
                j.go_next();
            }
            // j указывает на prev для i
            prevs[k] = j.get();
        }
    }
}

std::ostream &operator<<(std::ostream &ostream, const TText &text) {
    return ostream<<*(text.root);
}

char *TText::copy(int count, TTextIterator i) {
    char* result = new char[i.get_str_len(count)];
    int copied = 0;
    int index = 0;
    TStack<TTextNode*> stack;
    TStack<TSeparator> separators;
    TTextNode* current = i.get();
    // тк i может указывать на произвольный уровень нужно все уровни над ним положить в стек
    // мы можем подниматься только наверх, а в стеке сверху лежит наименьший уровень
    // поэтому используем очередь чтобы потом правильно заполнить текст
    TQueue<TTextNode*> queue;
    TTextIterator j = i;
    NodeLevel level = j.get()->get_level();
    level = static_cast<NodeLevel>(static_cast<int>(level)+1);
    while(level!=NodeLevel::TEXT){
        j.reset_to(level);
        queue.push(j.get());
        level = static_cast<NodeLevel>(static_cast<int>(level)+1);
    }
    while(!queue.is_empty()){
        TTextNode* node = queue.pop();
        stack.push(node);
        separators.push(node->get_separator());
    }

    while(current && (copied < count)){
        while(!current->is_letter()){
            stack.push(current);
            separators.push(current->get_separator());
            current = current->get_down();
        }
        while((current != nullptr) && (copied < count)){
            result[index] = current->get_c();
            copied++;
            index++;
            current= current->get_next();
        }
        while(true){
            if(!stack.is_empty()){
                current = stack.pop()->get_next();
                TSeparator s = separators.pop();
                if(current != nullptr){
                    for (int j = 0; j < s.get_len(); ++j) {
                        result[index] = s.get_s()[j];
                        index++;
                    }
                    // есть следующий обьект, обрабатываем его
                    break;
                }else if(current == nullptr && !stack.is_empty()){
                    // дошли до последнего слова(строки) и надо подниматься еще выше
                    continue;
                }else{
                    break;
                }
            }else{
                break;
            }
        }
    }
    result[index] = '\0';
    return result;
}
