import java.util.*;
import java.lang.*;
class QuarterlySales {
public static void main(String[] args) {
int sum = 0;
for (int i = 2; i <= 4; i++) {
sum += getMonthlySales(i);
}
System.out.println("Sum: "+sum);
}
public static int getMonthlySales(int month) {
return 100 * month;
}
}