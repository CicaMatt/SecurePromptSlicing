package com.company;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner input= new Scanner(System.in);
        System.out.println("Enter Index to get value");
        int index =input.nextInt();
        int [] id_sequence={1,2,3,4};
        System.exit(getValueAt(id_sequence,index));
    }
    public static int getValueAt (int[] array,int index){
        return array[index];
    }
}


### Explanation:
The program takes an integer from the standard input. This integer is used as a parameter to call the `getValueAt` function which returns the value at that position in the `id_sequence` array. The program then exits with the return value of the `getValueAt` function.