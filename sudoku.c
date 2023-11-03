#include <stdio.h>
#define SIZE 9

int board[ SIZE ][ SIZE ];
int checkRow( int row ) {
int freq[ SIZE + 1 ] = { 0 }; // 0 to 9, 0 is ignored
for ( int col = 0; col < SIZE; col++ ) {
    if ( freq[ board[ row ][ col ] ] == 1 ) return 0;
    freq[ board[ row ][ col ] ] = 1;
}
return 1;
}

int checkCol( int col ) {
    int freq[ SIZE + 1 ] = { 0 };
    for ( int row = 0; row < SIZE; row++ ) {
        if ( freq[ board[ row ][ col ] ] == 1 ) return 0;
        freq[ board[ row ][ col ] ] = 1;
    }
    return 1;
}

int checkSubgrid( int startRow , int startCol ) {
    int freq[ SIZE + 1 ] = { 0 };
    for ( int row = 0; row < 3; row++ ) {
        for ( int col = 0; col < 3; col++ ) {
            if ( freq[ board[ row + startRow ][ col + startCol ] ] == 1 ) return 0;
            freq[ board[ row + startRow ][ col + startCol ] ] = 1;
        }
    }
    return 1;
}

int isValidSudoku() {
    for ( int i = 0; i < SIZE; i++ ) {
        if ( !checkRow( i ) || !checkCol( i ) ) return 0;
    }
    for ( int i = 0; i < SIZE; i += 3 ) {
        for ( int j = 0; j < SIZE; j += 3 ) {
            if ( !checkSubgrid( i , j ) ) return 0;
            }
    }
    return 1;
}

int main( int argc, char *argv[] ) {
    FILE *filePointer;
    filePointer = fopen( argv[ 1 ] , "r" );
    char buffer[ 255] ; // Increased buffer size to accommodate '\n'

    if (filePointer == NULL) {
        printf( "Cannot read the file\n" );
        return 1;
    }

    int row = 0;
    int rowUnder = -1;
    int colUnder = -1;
    // read the file line by line
    while ( row < SIZE && fgets( buffer , sizeof( buffer ) , filePointer ) != NULL ) {
        int col = 0;
        int counter = 0;
        // adding data to each column in the board array
        while ( col < SIZE && ( buffer[ counter ] != '\n' || buffer[ counter ] != '\0' || buffer[ counter ] != EOF ) ) {
            if ( buffer[ counter ] >= '1' && buffer[ counter ] <= '9' ) {
                board[ row ][ col ] = buffer[ counter ] - '0'; // gives ASCII difference
                col++;
            }else if( buffer[ counter ] == '_' ){
                rowUnder = row;
                colUnder = col;
                board[ row ][ col ] = 0;
                col++;
            }
            counter++;
        }
        row++;
    }

    fclose( filePointer ); // close the pointer reading the file

    if( rowUnder == -1 ){
        if ( isValidSudoku() ) {
            printf( "correct\n" );
        } else {
            printf( "incorrect\n" );
        }
    }else{
        for( int i = 1; i < 10; i++ ){
            board[ rowUnder ][ colUnder ] = i;
            if ( isValidSudoku () ) {
                printf( "solvable\n" );
                return 0;
            }
        }
        printf( "unsolvable") ;
    }
    return 0;
}