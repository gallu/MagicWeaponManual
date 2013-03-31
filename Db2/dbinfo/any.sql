-- MagicWeaponManual用
-- SQL一式

-- まず文字コードを指定
SET NAMES utf8;

-- レシートテーブル
DROP TABLE IF EXISTS sales_receipt;
CREATE TABLE sales_receipt (
  `sales_receipt_id` varbinary(64) NOT NULL COMMENT '一意なレシート用ID',
  `user_id` varbinary(64) NOT NULL COMMENT 'ユーザID',
  `account_title_id` varbinary(64) NOT NULL COMMENT '科目ID',
  `amount` int NOT NULL COMMENT '金額',
  `sales_receipt_date` date NOT NULL COMMENT 'レシート日付',
  PRIMARY KEY (`sales_receipt_id`)
)CHARACTER SET 'utf8', ENGINE=InnoDB, COMMENT='１レコードが１レシートなテーブル';

