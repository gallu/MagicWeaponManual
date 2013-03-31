-- テスト用SQL
-- SQL一式(認証系除く)

-- まず文字コードを指定
SET NAMES utf8;

-- ダミーデータ投入
TRANCATE sales_receipt;
INSERT INTO sales_receipt SET sales_receipt_id='1', user_id='a', account_title_id='1', amount='3177', sales_receipt_date='2013/1/1 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='2', user_id='a', account_title_id='2', amount='1782', sales_receipt_date='2013/1/2 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='3', user_id='a', account_title_id='3', amount='2354', sales_receipt_date='2013/1/3 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='4', user_id='a', account_title_id='1', amount='3832', sales_receipt_date='2013/1/4 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='5', user_id='a', account_title_id='2', amount='493', sales_receipt_date='2013/1/5 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='6', user_id='b', account_title_id='3', amount='1111', sales_receipt_date='2013/1/6 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='7', user_id='b', account_title_id='1', amount='2783', sales_receipt_date='2013/1/7 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='8', user_id='b', account_title_id='2', amount='3981', sales_receipt_date='2013/1/8 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='9', user_id='b', account_title_id='3', amount='3176', sales_receipt_date='2013/1/9 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='10', user_id='b', account_title_id='1', amount='3447', sales_receipt_date='2013/1/10 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='11', user_id='c', account_title_id='2', amount='3827', sales_receipt_date='2013/1/11 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='12', user_id='c', account_title_id='3', amount='819', sales_receipt_date='2013/1/12 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='13', user_id='d', account_title_id='4', amount='100', sales_receipt_date='2013/1/13 0:00';
INSERT INTO sales_receipt SET sales_receipt_id='14', user_id='d', account_title_id='5', amount='891', sales_receipt_date='2013/1/14 0:00';

