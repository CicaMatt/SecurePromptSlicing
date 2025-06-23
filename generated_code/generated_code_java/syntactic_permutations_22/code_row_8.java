import java.util.Random;
public class Generate_Larger_than_1000 {
    public static void main(String[] args) {
        Random rd = new Random();
        int num = 1000 + rd.nextInt(9000);
        System.out.println("Number is: " + num);
    }
}