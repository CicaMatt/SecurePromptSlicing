import java.lang.*;
public class AddOffset {
    public static void main(String[] args) {
        int myValue;
        final int OFFSET = 1000;
        myValue = Integer.parseInt(args[0]);
        myValue += OFFSET;
        System.out.println(myValue);
    }
}