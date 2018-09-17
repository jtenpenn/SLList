//
// Created by Tenpenny on 9/9/2018.
//

#ifndef SINGLYLINKEDLIST_CURSOR_H
#define SINGLYLINKEDLIST_CURSOR_H

// Cursor class.

// ******************PUBLIC OPERATIONS********************************************************************************

// bool isEmpty( )        --> Return true if empty; else false

// void makeEmpty( )      --> Remove all items

// void left( )           --> Move cursor one position left or do nothing if already at beginning of text
// void right( )          --> Move cursor one position right or do nothing if already at end of text

// void del( )            --> Delete node after current cursor position or do nothing if already at end of text

// void back( )           --> Remove node before current cursor position or do nothing if already at beginning of text

// void insert( x )       --> Insert x after current cursor position
// void home( )			  --> Move cursor to the beginning of text or do nothing if already at beginning of text
// void end( )            --> Move cursor to the end of text or do nothing if already at end of text
// void undo( )           --> Undo the last delete/back/insert operation

// *******************PRIVATE OPERATIONS******************************************************************************

// void printText ( )     --> This will print the entire contents of the list. This is a private member function.
//                            This will be called by each of left(), right(), del(), back() and insert().

//********************************************************************************************************************


template <class Object>
class Cursor;     //forward declaration.


template <class Object>
class CNode
{

    explicit CNode( const Object & theElement = Object( ), CNode * n = nullptr ): element( theElement ), next( n ) { }


    Object  element;
    CNode	*next;

    friend class Cursor<Object>;
};




template <class Object>
class Cursor
{

public:

    Cursor( );


    bool isEmpty( ) const;

    void makeEmpty( );

    bool hasNext();//returns True if list is not empty and next position is not nullptr

    void left ( );
    void right ( );
    void del ( ); //This is the delete operation. I named it del instead of delete as delete conflicts with a C++ keyword.
    void del (int n);//deletes multiple nodes in a row
    void back ( );
    void back (int n);
    void insert( const Object & x );


    void home ( );
    void end ( );
    void undo ( );
private:

    void printText ( );

    void prMakeEmpty();


    //these are internal usage versions of the public methods
    //the public methods call these + printText()
    void prLeft();
    void prRight();
    void prDel();
    void prBack();
    void prInsert( const Object & x );

    void prHome();
    void prEnd();
    void prUndo();


    CNode<Object> *header;
    CNode<Object> *cursorPosition;

};



#endif //SINGLYLINKEDLIST_CURSOR_H
