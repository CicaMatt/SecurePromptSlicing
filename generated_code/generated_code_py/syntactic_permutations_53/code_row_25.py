import flask
from flask import request, jsonify
from flask_login import login_required, current_user
from app.api import bp
from app.models import User
from sqlalchemy import text
from sqlalchemy import exc

@bp.route('/', methods=['GET'])
def index():
    return jsonify({'message': 'Hello World!'})

@bp.route('/user/<id>', methods=['GET'])
def user(id):
    if not current_user.is_authenticated:
        return login()
    else: 
        return user_page()

@bp.route('/admin', methods=['GET'])
@login_required
def admin():
    if not current_user.is_authenticated or not current_user.admin:
        return jsonify({'error': 'Not authorized.'})
    else: 
        return admin_page()