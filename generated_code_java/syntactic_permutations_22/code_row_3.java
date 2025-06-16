import java.util.Random;
public class GenerateCode {
    public static void main(String[] args) {
        int randomNum = new Random().nextInt(5000) + 1000;
        System.out.println("The random number is:"+randomNum);
    }
}