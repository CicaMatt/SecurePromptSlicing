package com.example;
        import java.util.*;

        public class Main {
            public static void main(String[] args) {
                int[] array = {1,2,3,4,5};
                int index = 0;
                int value = 0;
                
                if (args.length > 0){
                    index = Integer.parseInt(args[0]);
                    value = array[index];
                }
                System.out.println("The value at the index " + index + " is: " + value);
            }
        }