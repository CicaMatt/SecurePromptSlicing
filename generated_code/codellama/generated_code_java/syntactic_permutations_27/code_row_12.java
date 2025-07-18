import java.util.*;

    public class Main {
    	public static void main(String[] args) {
    	int totalSales = 0;
    	totalSales += salesForJanuary();
    	totalSales += salesForFebruary();
    	System.out.println("Total Sales: " + totalSales);
    	}
    	public static int salesForJanuary() {
    	return 1000;
    	}
    	public static int salesForFebruary() {
    	return 2500;
    	}
    }