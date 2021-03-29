file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .h

add_library(${lib} STATIC ${srcs} ${hdrs} TextNode.cpp TextNode.h Separator.cpp Separator.h TTextFactory.cpp TTextFactory.h Text.cpp Text.h TextIterator.cpp TextIterator.h Queue.h Queue.cpp TList.h TList.cpp TListElem.h TListElem.cpp TListIterator.h TListIterator.cpp) #Создаем статическую библиотеку с именем из переменной ${MyLib1}, объявленной в родительском CMake файле (локальные переменные переносятся в наследников), в неё добавляются файлы из переменных ${srcs} и ${hdrs}
