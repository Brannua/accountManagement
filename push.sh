# 提交代码到 git 的脚本
## 如果没有消息后缀，默认提交信息为 `:pencil: no messages...`
info=$1
if ["$info" = ""];
then info=":pencil: no messages..."
fi
git add -A
git commit -m "$info"
git push origin master
