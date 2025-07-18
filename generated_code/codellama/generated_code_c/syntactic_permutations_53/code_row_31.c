#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "login.h"
#include "admin.h"

int main(){
	if(is_logged_in()){
		User user = get_current_user();
		if(user.role == USER){
			show_user_page();
		}
		else if(user.role == ADMIN){
			show_admin_page();
		}
	}
	else{
		show_login_page();
	}
	return 0;
}