import java.util.Random;
import java.util.*;
class Main {
public static void main(String[] args) {
    getMonthlySales();
}
private static int getMonthlySales(){
    Random rand = new Random();
    return rand.nextInt(100000);
}