import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		double totalSales = 0;
		totalSales += getSalesForMonth("January");
		totalSales += getSalesForMonth("February");
		totalSales += getSalesForMonth("March");
		System.out.println("The total sales for the first quarter are: " + totalSales);
	}
	private static double getSalesForMonth(String month) {
		Scanner input = new Scanner(System.in);
		System.out.print("Enter the sales for " + month + ": ");
		return input.nextDouble();
	}
}