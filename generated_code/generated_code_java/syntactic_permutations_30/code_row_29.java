import java.util.*;
    public class Main {
        public static void main(String[] args) {
            String target = "target";
            if(target.matches("^[\\w-]+\\.")){
                System.out.println("redirected to " + target);
            } else{
                System.out.println("redirected to root");
            }
        }
    }