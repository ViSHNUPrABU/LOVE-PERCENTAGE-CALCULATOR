#include<stdio.h>
#include<string.h>
#include<ctype.h>
void love_percentage_calculator()
{
    int length_of_combined_name,resulting_percentage;

    int first_index,last_index,number_of_loops;

    int quotient,remainder;

    int same_letter_count[50],length_of_same_letter_count=0;     //if there are two "d" then 2 , likewise storing every letters count in array

    char first_name[100],second_name[100],space_bar=' ';

    char loves[]="loves",combined_name[205]="";

    getchar();

    printf("\nEnter the First Name :");      //Getting first name from user
    gets(first_name);

    printf("\nEnter the Second Name :");      //Getting second name from user
    gets(second_name);

    strcpy(combined_name,first_name);          //combining all two name with middle as loves
    strcat(combined_name,loves);               //ex:first_name="Ajay",loves="loves",second_name="Pooja"
    strcat(combined_name,second_name);         //combined_name=AjaylovesPooja

    length_of_combined_name=strlen(combined_name);

    for(int l=0;l<length_of_combined_name;l++)              //changing every uppercase letter to lower in combined_name
      {
          if(combined_name[l]==space_bar)                  // replacing space bar with asterick so that it doesn't counts with letters
               combined_name[l]='*';
          combined_name[l]=tolower(combined_name[l]);
      }

    for(int i=0;i<length_of_combined_name;i++)
    {
        if(combined_name[i]=='*')          //if letter is asterick then it is useless to compare with others because it is repeated or a space bar
                continue;                  //so it moves to next loop
        same_letter_count[length_of_same_letter_count]=1;
        for(int j=i+1;j<length_of_combined_name;j++)
        {
            if(combined_name[j]=='*')             //if letter is asterick then it goes to next loop because it is repeated or may be a space bar
                continue;
            if(combined_name[i]==combined_name[j])
            {
                combined_name[j]='*';                   //replacing same letters with asterick(*) so that it is not counted again
                same_letter_count[length_of_same_letter_count]++;
            }
        }
        length_of_same_letter_count++;                        //increments length after every same letter is counted and replaced with asterick(*)
    }

    while(length_of_same_letter_count>2)                //loop runs until only two numbers are there after adding
    {
        if(length_of_same_letter_count%2==0)
            number_of_loops=length_of_same_letter_count/2;
        if(length_of_same_letter_count%2==1)                    //if number of same letter count is odd,then the center element is not added it is idle
            number_of_loops=(length_of_same_letter_count-1)/2;       //so only (n-1)/2 loops occur

        last_index=length_of_same_letter_count-1;
        for(first_index=0;first_index<number_of_loops;first_index++)
        {
                same_letter_count[first_index] += same_letter_count[last_index];      //adds the first and last letter and it stored in first letter
                last_index--;                                                     //ex: 5  2  3  1 ->  6  5 (only two digit remains so
        }                                                                   //love percentage is 65 % )
            length_of_same_letter_count=last_index+1;
        for(int index=0;index<length_of_same_letter_count;index++)         //This loop separates double digits into single digits
        {                                                                //ex:  5   7   8   9  -> 14  15  -> 1   4   1   5 -> 6  5 (65%)
            last_index=length_of_same_letter_count-1;
             if(same_letter_count[index]>9)
             {
                 quotient=same_letter_count[index]/10;
                 remainder=same_letter_count[index]%10;
                 for(int separate=last_index+1;separate>index+1;separate--)
                     same_letter_count[separate]=same_letter_count[separate-1];

                 same_letter_count[index]=quotient;
                 same_letter_count[index+1]=remainder;

                 length_of_same_letter_count++;
             }
        }
    }

    resulting_percentage=(10*same_letter_count[0])+same_letter_count[1];     //It stores the resultant two numbers in percentage.ex: 5 1 2 ->7 1 -> 71%
    printf("\n\t-------------------------------------------------------------------------------");
    printf("\n\t\tThe love percentage between %s and %s is %d %% ",first_name,second_name,resulting_percentage);
    printf("\n\t-------------------------------------------------------------------------------");
}
void main()
{
    char ch='y';

    printf("--------------LOVE_____PERCENTAGE____CALCULATOR---------------");
    printf("\n\nPress Enter to start :");

    while(ch=='y')
    {
        love_percentage_calculator();
        printf("\nDo you want to calculate Love Percentage again [y/n] :");
        scanf("%c",&ch);
    }
}
