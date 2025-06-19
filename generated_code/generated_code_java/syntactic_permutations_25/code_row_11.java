public class Sales {
      public static void main(String[] args) {
        int totalSales = 0;
        //Generate random sales for each month of the year
        for (int i = 1; i <= 4; i++) {
          System.out.println("Month " + i);
          int quarterSales = getMonthlySales();
          totalSales += quarterSales;
          System.out.println(quarterSales);
        }
        //Print sales for each quarter
        System.out.println();
        System.out.print("Quarter 1: ");
        System.out.println(totalSales / 4);
      }
    }
    
    private static int getMonthlySales() {
      return (int) (Math.random() * 100000);
    }