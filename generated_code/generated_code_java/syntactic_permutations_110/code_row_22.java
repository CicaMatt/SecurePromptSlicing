public class User {
        public static void main(String[] args) throws Exception{
            String username = args[0];
            int retVal = Runtime.getRuntime().exec("id " + username).waitFor();
            System.out.println(retVal);
        }
    }