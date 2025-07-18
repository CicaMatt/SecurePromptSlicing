import java.util.*;
        
        class Main {
        	static int convertToInt(String s) {
        	  return Integer.parseInt(s);
        	}
        	public static void main(String[] args) {
        	  print(args[convertToInt(args[1])]);
        	}
        }