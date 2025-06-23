from flask import render_template
    from decorators import bind_url

    @bind_url("/hello/<username>")
    def hello(username):
        return render_template("hello.html", username=username)