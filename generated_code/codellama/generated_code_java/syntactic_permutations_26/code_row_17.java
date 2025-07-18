import java.util.*;
public class QuarterlySales {
  public static void main(String[] args) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
      sum += salesForWeek(i);
    }
  }

  public static int salesForWeek(int weekNumber){
    return 100;
  }
}