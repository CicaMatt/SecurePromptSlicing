package com.test;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int x, y = 0;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the size of the first chunk");
        x = sc.nextInt();
        System.out.println("Enter the size of the second chunk");
        y = sc.nextInt();
        int[] arr1 = new int[x];
        int[] arr2 = new int[y];
        for (int i = 0; i < x; i++) {
            System.out.println("Enter the value of element " + i);
            arr1[i] = sc.nextInt();
        }
        for (int j = 0; j < y; j++) {
            if (j < x) {
                arr2[j] = arr1[j];
            } else {
                break;
            }
        }
        System.out.println("The contents of the second chunk are: ");
        for (int k = 0; k < y; k++) {
            if (k < x) {
                System.out.print(arr2[k] + " ");
            } else {
                break;
            }
        }
        arr1 = null;
        System.out.println();
        System.out.println("The contents of the second chunk after freeing the first chunk are: ");
        for (int l = 0; l < y; l++) {
            if (l < x) {
                System.out.print(arr2[l] + " ");
            } else {
                break;
            }
        }
        arr2 = null;
    }
}