package com.turing;

    public class Answer {

        public static void main(String[] args) {
            int[] numbers = new int[]{1,2,3,4,5};
            int input = 3; //input will be taken as an argument in the array;
            System.out.println("The value at index "+input+" is: "+numbers[input-1]);
        }
    }