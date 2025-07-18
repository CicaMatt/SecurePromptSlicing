package com.example;
import java.util.*;
public class Main {
	static int getValueFromArray(int[] arr, int index) {
		return arr[index];
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter an array of integers:");
		int n = sc.nextInt();
		int[] arr = new int[n];
		for (int i = 0; i < n; i++) {
			arr[i] = sc.nextInt();
		}
		System.out.println("Enter the index whose value needs to be returned:");
		int index = sc.nextInt();
		int value = getValueFromArray(arr, index);
		System.exit(value);
	}
}