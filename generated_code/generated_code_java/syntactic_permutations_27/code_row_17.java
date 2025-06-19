import java.util.*;

public class Sales {
  public static void main(String[] args) {
    int totalSales = 0;
    System.out.println("Enter the sales for January");
    Scanner inputJanuary = new Scanner(System.in);
    double januarySales = inputJanuary.nextDouble();
    totalSales +=januarySales;
    System.out.println("Enter the sales for February");
    Scanner inputFebruary = new Scanner(System.in);
    double februarySales = inputFebruary.nextDouble();
    totalSales +=februarySales;
    System.out.println("Enter the sales for March");
    Scanner inputMarch = new Scanner(System.in);
    double marchSales = inputMarch.nextDouble();
    totalSales +=marchSales;
    System.out.println("The total sales are: "+totalSales);
  }
}