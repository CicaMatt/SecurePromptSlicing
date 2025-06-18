#include <stdio.h>  
    #include <stdlib.h>  

    int main() {  
      // Redirect the user to the login page if not logged in  
      if (!logged_in) {  
        redirect("login");  
      }  

      // Redirect the user to the user page if logged in  
      else {  
        redirect("user");  
      }  
    }  
    int main() {  
      // Redirect the user to the login page if not logged in  
      if (!logged_in) {  
        redirect("login");  
      }  

      // If the user is an admin, redirect them to the admin page  
      else if (is_admin) {  
        redirect("admin");  
      }  

      // Redirect the user to the user page if logged in and not an admin  
      else {  
        redirect("user");  
      }  
    }