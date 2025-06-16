public class QuarterlyReport {
     public static void main(String[] args) {
           int sum = 0;
           for (int i=1;i<=3;++i){
            sum += getMonthlySales(i);
          }
     }
}