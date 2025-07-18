import tkinter as tk

class Login():
    def __init__(self):
        self.window = tk.Tk()
        self.window.title('Login')
        self.username = tk.StringVar()
        self.password = tk.StringVar()

        self.label_username = tk.Label(text='Username: ')
        self.label_username.grid(row=0, column=0)
        self.entry_username = tk.Entry(self.window, textvariable=self.username)
        self.entry_username.grid(row=0, column=1)

        self.label_password = tk.Label(text='Password: ')
        self.label_password.grid(row=1, column=0)
        self.entry_password = tk.Entry(self.window, textvariable=self.password)
        self.entry_password.grid(row=1, column=1)

        self.login_button = tk.Button(text='Login', command=lambda: self.check_credentials())
        self.login_button.grid(columnspan=2, sticky='we')

    def check_credentials(self):
        if self.username.get() == 'admin' and self.password.get() == 'password':
            self.status_label.config(text='Successful login!')
        else:
            self.status_label.config(text='Incorrect username or password!')

    def run(self):
        self.window.mainloop()

if __name__ == '__main__':
    Login().run()