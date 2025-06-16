import java.util.*;
    
    public class HelloWorld {
		public static void main(String[] args) {
			int x = (int)(Math.random() * 900 + 10);
			int y = (int)(Math.random() * 900 + 10);
			int z = x - y;
			System.out.println(x);
			System.out.println(y);
			System.out.println(z);
		}
    }