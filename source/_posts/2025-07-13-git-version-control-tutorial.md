---
title: Git 版本控制完全指南
date: 2025-03-17 12:00:00 +0800
categories: [Learning, Tools]
tags: [git, github]
description: Git 版本控制完全指南，从入门到精通，包含创建版本库、时光机穿梭、分支管理、远程仓库管理等核心概念和常用命令
toc: true
---

# Git 版本控制完全指南

## 一、什么是版本控制

版本控制是一种记录一个或若干文件内容变化，以便将来查阅特定版本修订情况的系统。

## 二、创建版本库

### 2.1 创建空目录

```bash
mkdir learngit
cd learngit
```

### 2.2 初始化为 Git 仓库

```bash
git init
```

### 2.3 把文件添加到仓库

```bash
git add README.txt
```

### 2.4 把文件提交到仓库

```bash
git commit -m "wrote a readme file"
```

> [!TIP]
> `-m` 后面输入的是本次提交的说明，可以输入任意内容，当然最好是有意义的，这样你就能从历史记录里方便地找到改动记录。

`commit` 可以一次提交很多文件，所以你可以多次 `add` 不同的文件：

```bash
git add file1.txt
git add file2.txt file3.txt
git commit -m "add 3 files."
```

> [!NOTE]
> `git add` 命令实际上就是把要提交的所有修改放到暂存区（Stage），然后执行 `git commit` 就可以一次性把暂存区的所有修改提交到分支。

每次修改，如果不用 `git add` 到暂存区，那就不会加入到 `commit` 中。

**工作流程**：第一次修改 → `git add` → 第二次修改 → `git add` → `git commit`

## 三、时光机穿梭

### 3.1 查看仓库状态

```bash
git status
```

可以查看仓库当前状态

### 3.2 查看文件修改

```bash
git diff README.txt
```

可以查看做了什么修改

### 3.3 查看历史记录

```bash
git log
```

可以查看历史记录（从最近到最远）

在 Git 中，用 `HEAD` 表示当前版本，也就是最新的提交：
- `HEAD^`：上一个版本
- `HEAD^^`：上上一个版本
- `HEAD~100`：往上 100 个版本

### 3.4 版本回退

把当前版本回退到上一个版本：

```bash
git reset --hard HEAD^
```

> [!NOTE]
> `--hard` 参数会回退到上个版本的已提交状态
> - `--soft`：会回退到上个版本的未提交状态
> - `--mixed`：会回退到上个版本已添加但未提交的状态

### 3.5 回到未来

找到要回到的版本号（之前执行 `git log` 时显示的）：

```bash
git reset --hard 1094a
```

要是找不到了，可以使用 `git reflog` 查看之前的命令历史。

### 3.6 撤销工作区修改

```bash
git checkout -- readme.txt
```

命令 `git checkout -- readme.txt` 意思就是，把 `readme.txt` 文件在工作区的修改全部撤销。

**两种情况**：
1. `readme.txt` 自修改后还没有被放到暂存区，撤销修改就回到和版本库一模一样的状态
2. `readme.txt` 已经添加到暂存区后，又作了修改，撤销修改就回到添加到暂存区后的状态

总之，就是让这个文件回到最近一次 `git commit` 或 `git add` 时的状态。

> [!WARNING]
> `git checkout -- file` 命令中的 `--` 很重要，没有 `--`，就变成了"切换到另一个分支"的命令

### 3.7 撤销暂存区修改

用命令 `git reset HEAD <file>` 可以把暂存区的修改撤销掉（unstage），重新放回工作区。

## 四、分支管理

### 4.1 创建和切换分支

```bash
git branch <branch-name>      # 创建分支
git checkout <branch-name>    # 切换分支
git checkout -b <branch-name> # 创建并切换分支
```

### 4.2 合并分支

```bash
git merge <branch-name>
```

### 4.3 删除分支

```bash
git branch -d <branch-name>   # 删除本地分支
git branch -D <branch-name>   # 强制删除
git push origin --delete <branch-name> # 删除远程分支
```

## 五、远程仓库

### 5.1 关联远程仓库

```bash
git remote add origin git@server-name:path/repo-name.git
```

> [!NOTE]
> 关联一个远程库时必须给远程库指定一个名字，`origin` 是默认习惯命名

### 5.2 推送内容

第一次推送 `master` 分支的所有内容：

```bash
git push -u origin master
```

此后，每次本地提交后，只要有必要，就可以使用命令推送最新修改：

```bash
git push origin master
```

### 5.3 查看远程仓库

```bash
git remote -v
```

示例输出：

```
origin  git@github.com:michaelliao/learn-git.git (fetch)
origin  git@github.com:michaelliao/learn-git.git (push)
```

### 5.4 删除远程仓库

如果添加的时候地址写错了，或者就是想删除远程库，可以用 `git remote rm <name>` 命令：

```bash
git remote rm origin
```

> [!NOTE]
> 此处的"删除"其实是解除了本地和远程的绑定关系，并不是物理上删除了远程库。远程库本身并没有任何改动。要真正删除远程库，需要登录到 GitHub，在后台页面找到删除按钮再删除。

## 六、常用命令速查表

| 命令 | 说明 |
|------|------|
| `git init` | 初始化仓库 |
| `git add <file>` | 添加文件到暂存区 |
| `git commit -m "message"` | 提交到仓库 |
| `git status` | 查看仓库状态 |
| `git log` | 查看提交历史 |
| `git log --oneline` | 简洁显示历史记录 |
| `git log --graph` | 图形化显示历史记录 |
| `git diff <file>` | 查看文件修改 |
| `git reset --hard HEAD^` | 回退到上一版本 |
| `git reset --hard <commit>` | 回退到指定版本 |
| `git checkout -- <file>` | 撤销工作区修改 |
| `git reset HEAD <file>` | 撤销暂存区修改 |
| `git remote add origin <url>` | 关联远程仓库 |
| `git push -u origin master` | 首次推送到远程 |
| `git push origin master` | 推送到远程 |
| `git remote -v` | 查看远程仓库 |
| `git remote rm <name>` | 删除远程仓库 |
| `git reflog` | 查看命令历史 |
| `git branch <name>` | 创建分支 |
| `git checkout -b <name>` | 创建并切换分支 |
| `git merge <name>` | 合并分支 |
| `git branch -d <name>` | 删除分支 |
| `git revert <commit>` | 撤销提交 |

## 七、最佳实践

1. **频繁提交**：每次完成一个小功能就提交一次
2. **有意义的提交信息**：清楚地描述这次提交做了什么
3. **使用分支**：开发新功能时使用新分支
4. **推送前拉取**：推送前先拉取最新代码避免冲突
5. **备份重要代码**：及时推送到远程仓库
