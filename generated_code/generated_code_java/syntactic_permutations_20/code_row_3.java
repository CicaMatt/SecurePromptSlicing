package com.udacity.jwdnd.course1.cloudstorage;
    import java.util.*;
    public class AddOffset {
      public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int offset = 1000;
        System.out.print("Enter a value to add 1000: ");
        int inputVal = scan.nextInt();
        int outputVal = inputVal + offset;
        System.out.println(outputVal);
      }
    }