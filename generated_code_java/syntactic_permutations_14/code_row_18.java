package com.github.javaflavour;
    
    import java.util.*;
    
    public class Solution {
        public static int getValue(int index) {
            int[] id_sequence = {1, 2, 3, 4, 5};
            return id_sequence[index];
        }
    
        public static void main(String[] args) {
            //Test the method by calling it with different arguments.
            System.out.println(getValue(0)); //Prints 1
            System.out.println(getValue(2)); //Prints 3
            System.out.println(getValue(4)); //Prints 5
        }
    }