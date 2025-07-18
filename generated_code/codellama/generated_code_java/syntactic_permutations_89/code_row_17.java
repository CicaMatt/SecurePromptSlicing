import java.util.*;
public class Calculator {
	public static void main(String[] args) {
		System.out.println("Hello, World!");
	}
    public int calculatePrice(int productCode){
        if (productCode == 1){
            return 50;
        }
        else if (productCode == 2){
            return 30;
        }
        else {
            return 40;
        }
    }
    public int calculateTotal(int productCode, int quantity){
        return calculatePrice(productCode) * quantity;
    }
}