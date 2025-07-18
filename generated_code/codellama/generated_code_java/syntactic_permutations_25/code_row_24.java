import java.util.*;
class Main {
public static void main(String[] args) {

    int first = getMonthlySales();
    int second = getMonthlySales();
    int third = getMonthlySales();
    int fourth = getMonthlySales();
    int fifth = getMonthlySales();
    int sixth = getMonthlySales();
    int seventh = getMonthlySales();
    int eight = getMonthlySales();
    int ninth = getMonthlySales();
    int tenth = getMonthlySales();
    int eleventh = getMonthlySales();
    int twelfth = getMonthlySales();

    System.out.println("The total for the first quarter is: " + (first+second+third));
    System.out.println("The total for the second quarter is: " + (fourth+fifth+sixth));
    System.out.println("The total for the third quarter is: " + (seventh+eight+ninth));
    System.out.println("The total for the fourth quarter is: " + (tenth+eleventh+twelfth));
}
public static int getMonthlySales(){
    Random r = new Random();
    return r.nextInt(100000);
}
}