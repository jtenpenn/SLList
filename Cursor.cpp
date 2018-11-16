//
// Created by Tenpenny on 9/9/2018.
//

#include "Cursor.h"

//start public methods
template<class Object>
Cursor<Object>::Cursor() {//default
    this->header = nullptr;
    this->cursorPosition = nullptr;
}

template<class Object>
Cursor<Object>::Cursor(const Cursor<Object> &c) {//copy constructor
    if(c.isEmpty()){
        this->header = nullptr;
        this->cursorPosition = nullptr;
        return;
    }

    CNode<Object> *inTmp = c.header;//iterates over old

    this->header = new CNode<Object>(inTmp->element, nullptr);//copy the head over
    CNode<Object> *outTmp = this->header;//iterates over new

    //copy the rest of the list
    inTmp = inTmp->next;
    while(inTmp != nullptr){
        outTmp->next = new CNode<Object>(inTmp->element, nullptr);
        outTmp = outTmp->next;
        if(inTmp == c.cursorPosition){
            this->cursorPosition = outTmp;
        }
        inTmp = inTmp->next;
    }
}

template<class Object>
Cursor<Object>::Cursor(const Cursor<Object> &&c)noexcept{//move constructor
    Cursor();
    swap(*this,c);
}

template<class Object>
Cursor<Object>::~Cursor()
{
    this->cursorPosition = this->header;

    while(cursorPosition != nullptr)
    {
        cursorPosition = cursorPosition->next;
        delete header;
        header = cursorPosition;
    }
}

template<class Object>
Cursor<Object>& Cursor<Object>::operator=(Cursor<Object> c){
    swap(*this, c);
    return *this;
}

template<class Object>
bool Cursor<Object>::isEmpty() const {
    bool ret = !(this->header);
    return ret;
}

template<class Object>
void Cursor<Object>::makeEmpty() {
    this->save();
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
    this->save();
    this->prLeft();
    this->printText();
}

template<class Object>
void Cursor<Object>::right() {
    this->save();
    this->prRight();
    this->printText();
}

template<class Object>
void Cursor<Object>::del() {
    this->save();
    this->prDel();
    this->printText();
}

template<class Object>
void Cursor<Object>::del(int n) {
    this->save();
    for(int i = 0; i < n; i++) {
        this->prDel();
        this->prRight();
    }
    this->printText();
}


template<class Object>
void Cursor<Object>::back() {
    this->save();
    this->prBack();
    this->printText();

}

template<class Object>
void Cursor<Object>::back(int n) {
    this->save();
    for(int i = 0; i < n; i++) {
        this->prBack();
    }
    this->printText();
}

template<class Object>
void Cursor<Object>::insert(const Object &x) {
    this->save();
    this->prInsert(x);
    this->printText();

}

template<class Object>
void Cursor<Object>::home() {
    this->save();
    this->prHome();
    this->printText();
}

template<class Object>
void Cursor<Object>::end() {
    this->save();
    this->prEnd();
    this->printText();

}

template<class Object>
void Cursor<Object>::undo() {
    this->prUndo();
    this->printText();
}

template<class Object>
void Cursor<Object>::undo(int n) {
    for(int i = 0; i < n; i++) {
        this->prUndo();
    }
    this->printText();
}
//end public methods

//start private methods
template<class Object>
void Cursor<Object>::printText() {
    if(!this->isEmpty()) {
        CNode<Object> *printpointer = this->header;

        do{
            std::cout << printpointer->element;
            if(printpointer == cursorPosition){
                std::cout << '|';
            }
            printpointer = printpointer->next;
        }while(printpointer != nullptr);

    }else {std::cout << '|';}

    std::cout << std::endl;
}

template<class Object>
void Cursor<Object>::prMakeEmpty() {
    this->prHome();
    while(!this->isEmpty()){
        this->prBack();
    }

}


template<class Object>
void Cursor<Object>::prLeft() {
    if(this->cursorPosition != this->header) {
        CNode<Object> *tmp = this->cursorPosition;
        this->prHome();
        while (tmp != this->cursorPosition->next) {
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
        CNode<Object> *tmp = this->cursorPosition->next->next;
        delete this->cursorPosition->next;
        this->cursorPosition->next = tmp;
    }else{
        delete this->cursorPosition->next;
        this->cursorPosition->next = nullptr;
    }
}

template<class Object>
void Cursor<Object>::prBack() {
    if(!this->isEmpty()) {
        if (this->cursorPosition != this->header) {
            this->prLeft();
            this->prDel();
        } else {
            CNode<Object> *tmp = this->header->next;
            delete this->header;
            this->header = tmp;
        }
    }
}

template<class Object>
void Cursor<Object>::prInsert(const Object &x) {
    if(this->isEmpty()){
        auto *tmp = new CNode<Object>(x, nullptr);
        this->header = tmp;
        this->cursorPosition = header;
    }else {
        auto *tmp = new CNode<Object>(x, this->cursorPosition->next);
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
        this->prRight();
    }
}

template<class Object>
void Cursor<Object>::save() {
    if (state.size() >= 10) {
        state.pop_front();
    }
    state.emplace_back(*this);
}

template<class Object>
void Cursor<Object>::prUndo() {
    *this = state.back();
    state.pop_back();
}


//end private methods




