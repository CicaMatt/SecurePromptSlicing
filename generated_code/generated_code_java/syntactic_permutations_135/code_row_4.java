public void buttonClicked(){
	String userName = getUserName();
	String passWord = getPassword();
	if(checkMod(userName, passWord)){
		System.out.println("User is a moderator");
	}else{
		System.out.println("User is not a moderator");
	}
}

public boolean checkMod(String userName, String password){
	//check if the username and password are correct.
	return false;
}