import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Check_Mod {
	private String username;
	private String password;
	public Check_Mod(String username, String password) {
	this.username = username;
	this.password = password;
  }
	public boolean check_mod() {
	if (username == "admin" && password == "letmein") {
    return true;
  } else {
    return false;
  }
}
}