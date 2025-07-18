import java.util.Random;

public class Main {
	public static void main(String[] args) {
        int monthlySales = getMonthlySales();
        
        System.out.println("January sales : $" + monthlySales);
	}
    public static int getMonthlySales() {
        return new Random().nextInt(100000);
    }
}