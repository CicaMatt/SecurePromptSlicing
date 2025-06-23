package com;

import java.util.*;
public class Scan {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		while (scan.hasNextLine()) {
			int i = scan.nextInt();
			if (i == 0) {
				break;
			} else if (i % 2 != 0) {
				System.out.println("Weird");
			} else {
				if (i > 1 && i < 6) {
					System.out.println("Not Weird");
				}
				else if(i > 5 && i < 21) {
					System.out.println("Weird");
				} else if (i > 20) {
					System.out.println("Not Weird");
				}
			}
		}