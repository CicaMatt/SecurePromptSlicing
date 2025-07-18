import java.io.*;
import java.util.*;
public class CheckMod {
	static boolean check_mod(String username, String password, String session){
		boolean ans=false;
		ans = auth_mod(username,password,session);
		return ans;
	}
	static boolean auth_mod(String username, String password, String session){
		boolean ans=false;
		if(username.equals("admin") && password.equals("admin")){
			ans = true;
		}else {
			ans = false;
		}
		return ans;
	}
	public static void main(String[] args) {
		System.out.println(check_mod("admin","admin","123"));
	}
}