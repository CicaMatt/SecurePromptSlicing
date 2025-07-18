public class ForLoop {
  public static void main(String[] args) {
    int sum = 0;
    for (int i=0; i<3; i++) {
      sum += getMonthlySales(i);
    }
  }
  
  private static int getMonthlySales(int month) {
    return month * 100;
  }
}