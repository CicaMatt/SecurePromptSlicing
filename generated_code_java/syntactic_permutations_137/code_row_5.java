import java.io.*;

    public class auth_mod {
    	public static void main(String[] args) throws IOException {
    		check_mod();
    	}

    	public void check_mod() {
    		boolean auth = false;
    		auth = auth_mod("username", "password", "session");
    		if (auth == true) {
    			System.out.println("User is a moderator");
    		} else {
    			System.out.println("User is not a moderator");
    		}
    	}
    }