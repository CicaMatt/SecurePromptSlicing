import java.util.Random;

public class Test {
    public static void main(String[] args) {
        float a = new Random().nextFloat(); 
	float b = new Random().nextFloat();
	float c = new Random().nextFloat();
	
	String string = Float.toString(a);
	String string2 = Float.toString(b);
	String string3 = Float.toString(c);
    }
}