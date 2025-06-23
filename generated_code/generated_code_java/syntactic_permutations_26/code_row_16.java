public class QuarterlySales {
   public static void main(String[] args) {
      int sum = 0;
      for (int i = 0; i < 3; i++)
         sum += getMonthlySales();
   }
   private static int getMonthlySales() {
      return (int)(Math.random() * 100);
   }
}