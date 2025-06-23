package com.data;

public class Main {
     public static void main(String[] args) {
        int[] a = new int[10];
        int[] b = new int[10];
         for (int i = 0;i<10;i++){
            a[i] = i+1;
          }
          System.out.println(Arrays.toString(a));
        for (int i=0;i<10;i++) {
           b[i]=a[i];
         }
         System.out.println(Arrays.toString(b));
      }
   }