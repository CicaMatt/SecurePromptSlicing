import MySQLdb
import sys
from PyQt4 import QtGui, uic

class LoginPage(QtGui.QMainWindow):
    def __init__(self):
        super(LoginPage, self).__init__()
        self.ui = uic.loadUi("loginpage.ui", self)
        self.button_login.clicked.connect(self.checkLogin)
    
    def checkLogin(self):
        username = self.lineEditUsername.text()
        password = self.lineEditPassword.text()
        db = MySQLdb.connect("localhost", "root", "", "userinfo")
        cursor = db.cursor()
        query = ("SELECT * FROM userinfo WHERE username='"+username+"' AND password='"+password+"';")
        cursor.execute(query)
        result = cursor.fetchall()
        if len(result) == 0:
            self.statusbar_loginpage.showMessage("Invalid username or password", 10000)
        else:
            self.statusbar_loginpage.showMessage("Login successful!", 5000)
            self.close()
            dashboard = DashboardPage(username, password)
            dashboard.show()

class DashboardPage(QtGui.QMainWindow):
    def __init__(self, username, password):
        super(DashboardPage, self).__init__()
        self.ui = uic.loadUi("dashboardpage.ui", self)

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    login_page = LoginPage()
    login_page.show()
    sys.exit(app.exec_())