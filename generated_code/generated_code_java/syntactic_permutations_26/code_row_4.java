package codeguru;

import java.util.Scanner;

public class Exercise {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int i, sum = 0, sales = 0, count = 3;
        for (i = 0; i < count; i++) {
            sales = getMonthlySales();
            sum += sales;
            System.out.println("Total sales after " + (i + 1) + " months: $" + sum);
        }
    }

    public static int getMonthlySales() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the monthly sales amount in USD: ");
        return sc.nextInt();
    }
}