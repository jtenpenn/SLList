//
// Created by Tenpenny on 9/9/2018.
//

#include "Cursor.h"
//TODO I have almost certainly fucked up my usage of the dereference syntax
//start public methods
template<class Object>
Cursor<Object>::Cursor() {
    this->header = nullptr;
    this->cursorPosition = header;
}

template<class Object>
bool Cursor<Object>::isEmpty() const {
    return this->header != nullptr;
}

template<class Object>
void Cursor<Object>::makeEmpty() {
    this->prMakeEmpty();
    this->printText();

}

template<class Object>
bool Cursor<Object>::hasNext() {
    if (!this->isEmpty()){
        return (this->cursorPosition->next != nullptr);
    }
    return false;
}



template<class Object>
void Cursor<Object>::left() {
    this->prLeft();
    this->printText();
}

template<class Object>
void Cursor<Object>::right() {
    this->pRight();
    this->printText();
}

template<class Object>
void Cursor<Object>::del() {
        this->prDel();
        this->prRight();
        this->printText();
}

template<class Object>
void Cursor<Object>::del(int n) {
    for(int i = 0; i < n; i++) {
        this->prDel();
        this->prRight();
    }
    this->printText();
}


template<class Object>
void Cursor<Object>::back() {
    this->prBack();
    this->printText();

}

template<class Object>
void Cursor<Object>::back(int n) {
    this->prBack();
    this->printText();

}

template<class Object>
void Cursor<Object>::insert(const Object &x) {
    this->prInsert(x);
    this->printText();

}

template<class Object>
void Cursor<Object>::home() {
    this->prHome();
    this->printText();
}

template<class Object>
void Cursor<Object>::end() {
    this->prEnd();
    this->printText();

}

template<class Object>
void Cursor<Object>::undo() {
    this->prUndo();
    this->printText();

}
//end public methods

//start private methods
template<class Object>
void Cursor<Object>::printText() {//TODO

}

template<class Object>
void Cursor<Object>::prMakeEmpty() {//TODO needs testing
    this->prHome();
    CNode<Object> *next;

    while(this->cursorPosition != nullptr){
        next = this->cursorPosition->next;
        delete this->cursorPosition;
        this->cursorPosition = next;
    }
    this->header = nullptr;
    this->prHome();

}


template<class Object>
void Cursor<Object>::prLeft() {
    if(this->cursorPosition != this->header) {
        CNode<Object> *tmp = *this->cursorPosition;//TODO
        this->prHome();
        while (tmp->next != this->cursorPosition) {
            this->prRight();
        }
    }
}

template<class Object>
void Cursor<Object>::prRight() {
    if(this->hasNext()) {
        this->cursorPosition = this->cursorPosition->next;
    }
}

template<class Object>
void Cursor<Object>::prDel() {
    if(this->hasNext()) {
        CNode<Object> *tmp = *this->cursorPosition->next->next;//TODO
        delete this->cursorPosition->next;
        this->cursorPosition->next = tmp;
    }
}

template<class Object>
void Cursor<Object>::prBack() {
    if(this->cursorPosition != this->header) {
        CNode<Object> *tmp;//TODO
        tmp = *this->cursorPosition;
        this->prLeft();

    }
}

template<class Object>
void Cursor<Object>::prInsert(const Object &x) {
    CNode<Object> *tmp;//TODO
    if(this->isEmpty()){
        tmp = CNode<Object>(x, nullptr);
        this->header = tmp;
    }else {
        tmp = CNode<Object>(x, this->cursorPosition->next);
        this->cursorPosition->next = tmp;
        prRight();
    }
}

template<class Object>
void Cursor<Object>::prHome() {
    this->cursorPosition = header;
}

template<class Object>
void Cursor<Object>::prEnd() {
    while(this->hasNext()){
        this->pRight();
    }
}

template<class Object>
void Cursor<Object>::prUndo() {//TODO

}


//end private methods








