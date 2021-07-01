#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

void delay( float seconds )
{
    int milliseconds = 1000 * seconds;
    clock_t start_time = clock() ;
    while( clock() < start_time + milliseconds )
        ;
}

int letter_counter( char combined_name[] , int length_of_combined_name , int same_letter_count[] , int length_of_same_letter_count)
{
    for( int i = 0; i < length_of_combined_name ; i++ )
    {
        if( combined_name[i] == '*' )          //if letter is asterisk then it is useless to compare with others because it is repeated or a space bar
                continue;                  //so it moves to next loop
        same_letter_count[length_of_same_letter_count] = 1 ;

        for( int j = i+1 ; j < length_of_combined_name ; j++ )
        {
            if( combined_name[j] == '*' )             //if letter is asterisk then it goes to next loop because it is repeated or may be a space bar
                continue;
            if( combined_name[i] == combined_name[j] )
            {
                combined_name[j] = '*' ;                   //replacing same letters with asterisk(*) so that it is not counted again
                same_letter_count[length_of_same_letter_count]++ ;
            }
        }
        length_of_same_letter_count++ ;                        //increments length after every same letter is counted and replaced with asterisk(*)
    }

    for( int index = 0 ; index < length_of_same_letter_count ; index++ )         //This loop separates double and triple digits into single digits
    {                                                                         //ex:  121   17   2   8   9  -> 1  2  1  1  7  2  8  9
         int last_index = length_of_same_letter_count - 1 ;

         if( same_letter_count[index] > 99 )
         {
             int first_digit = same_letter_count[index] / 10 ;
             int third_digit = same_letter_count[index] % 10 ;
             int second_digit = first_digit % 10 ;
             first_digit = first_digit / 10 ;

             for( int separate = last_index + 2 ; separate > index + 2 ; separate-- )
                 same_letter_count[ separate ] = same_letter_count[ separate - 2 ] ;

             same_letter_count[ index ] = first_digit ;
             same_letter_count[ index + 1 ] = second_digit ;
             same_letter_count[ index + 2 ] = third_digit ;

             length_of_same_letter_count += 2 ;
         }

         else if( same_letter_count[index] > 9 )
         {
             int first_digit = same_letter_count[index] / 10 ;
             int second_digit = same_letter_count[index] % 10 ;
             for( int separate = last_index + 1 ; separate > index + 1 ; separate-- )
                 same_letter_count[separate] = same_letter_count[separate-1] ;

             same_letter_count[index] = first_digit ;
             same_letter_count[index+1] = second_digit ;

             length_of_same_letter_count++ ;
         }

    }

    return combined_name , length_of_combined_name , same_letter_count , length_of_same_letter_count ;
}

void percentage_calculator( int same_letter_count[] , int length_of_same_letter_count )
{

    while( length_of_same_letter_count > 2 )                //loop runs until only two numbers are there after adding
    {
        int first_index , last_index , number_of_loops , quotient , remainder ;

        if( length_of_same_letter_count % 2 == 0 )
            number_of_loops = length_of_same_letter_count/2 ;
        if( length_of_same_letter_count % 2 == 1 )                    //if number of same letter count is odd,then the center element is not added it is idle
            number_of_loops = (length_of_same_letter_count-1)/2 ;       //so only (n-1)/2 loops occur

        last_index = length_of_same_letter_count - 1 ;
        for( first_index = 0 ; first_index < number_of_loops ; first_index++ )
        {
                same_letter_count[first_index] += same_letter_count[last_index];      //adds the first and last letter and it stored in first letter
                last_index--;                                                     //ex: 5  2  3  1 ->  6  5 (only two digit remains so
        }                                                                   //love percentage is 65 % )
        length_of_same_letter_count = last_index + 1 ;
        for( int index = 0 ; index < length_of_same_letter_count ; index++ )         //This loop separates double digits into single digits
        {                                                                //ex:  5   7   8   9  -> 14  15  -> 1   4   1   5 -> 6  5 (65%)
             last_index = length_of_same_letter_count - 1 ;

             if( length_of_same_letter_count == 2 & same_letter_count[0] == 10 & same_letter_count[1] == 0 )
                 break;

             else if( same_letter_count[index] > 9 )
             {
                 quotient = same_letter_count[index] / 10 ;
                 remainder = same_letter_count[index] % 10 ;
                 for( int separate = last_index+1 ; separate > index+1 ; separate-- )
                     same_letter_count[separate] = same_letter_count[separate-1] ;

                 same_letter_count[index] = quotient;
                 same_letter_count[index+1] = remainder;

                 length_of_same_letter_count++;
             }
        }
    }
}

void percentage_loader( int resulting_percentage )
{
    for( int rolling_count = 1 ; rolling_count <= resulting_percentage ; rolling_count ++ )
    {
        if( rolling_count < 10 )
            printf("\b\b\b%d %%",rolling_count);

        if( rolling_count >= 10 )
            printf("\b\b\b\b\b %d %%",rolling_count);

        if( rolling_count == 100 )
            printf("\b\b\b\b\b\b %d %%",rolling_count);

        if( rolling_count > resulting_percentage - 2 )
            delay(0.40);

        else if( rolling_count > resulting_percentage - 6 )
            delay(0.25);

        else if( rolling_count > resulting_percentage - 9 )
            delay(0.125);

        else if( rolling_count > resulting_percentage - 29 )
            delay(0.1);

        else if( rolling_count > resulting_percentage - 49 )
            delay(0.075);

        else if( rolling_count > resulting_percentage - 69 )
            delay(0.05);
    }
}


int love_percentage_calculator()
{
    int length_of_combined_name , resulting_percentage ;

    int same_letter_count[205] , length_of_same_letter_count = 0 ;     //if there are two "d" then 2 , likewise storing every letters count in array

    char first_name[101] , second_name[101] , space_bar = ' ' ;   //100 characters and 1 for null termination

    char loves[] = "loves" , combined_name[206] = "" ;

    getchar();

    printf("\nEnter the First Name :");      //Getting first name from user
    gets(first_name);

    printf("\nEnter the Second Name :");      //Getting second name from user
    gets(second_name);

    if( strlen(first_name) > 100 | strlen(second_name) > 100 )
    {
        printf("\nYou have entered the name with more than 100 characters , please give a name with less than or equal to 100 characters.\n\n");
        return 0;
    }

    strcpy( combined_name, first_name );          //combining all two name with middle as loves
    strcat( combined_name, loves );               //ex:first_name="Ajay",loves="loves",second_name="Pooja"
    strcat( combined_name, second_name );         //combined_name=AjaylovesPooja

    length_of_combined_name = strlen(combined_name);

    for( int l = 0 ; l < length_of_combined_name ; l++ )              //changing every uppercase letter to lower in combined_name
      {
          if( combined_name[l] == space_bar )                  // replacing space bar with asterisk so that it doesn't counts with letters
               combined_name[l] = '*' ;
          combined_name[l] = tolower(combined_name[l]) ;
      }



    //getting same letter count and length of it because it is empty in this function and can't be modified in letter_counter function
    combined_name , length_of_combined_name , same_letter_count , length_of_same_letter_count = letter_counter( combined_name , length_of_combined_name , same_letter_count , length_of_same_letter_count );



    percentage_calculator( same_letter_count , length_of_same_letter_count );



    resulting_percentage = ( 10 * same_letter_count[0] ) + same_letter_count[1] ;     //It stores the resultant two numbers in percentage.ex: 5 1 2 ->7 1 -> 71%
    printf("\n\t%c--------------------------------------------------",201);
    for( int print = 1 ; print <= length_of_combined_name ; print++ )
        printf("-");
    printf("%c\n\t|       The love percentage between %s and %s is  0 %%",187,first_name,second_name);


    percentage_loader( resulting_percentage );

    if( resulting_percentage != 100 )
        printf(" ");
    printf("      |\n\t%c--------------------------------------------------",200);
    for( int print = 1 ; print <= length_of_combined_name ; print++ )
        printf("-");
    printf("%c\n",188);

}
void main()
{
    char ch = 'y' ;

    printf("----------------------LOVE_____PERCENTAGE____CALCULATOR-----------------------");
    printf("\n\nPress Enter to start :");

    while( ch == 'y' )
    {
        love_percentage_calculator();
        printf("\n\nDo you want to calculate Love Percentage again [y/n] :");
        scanf("%c",&ch);
    }
}
