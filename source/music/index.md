---
title: Music
date: 2026-03-27 12:00:00
type: "music"
comments: true
---

<div class="aplayer-container">
  <div id="aplayer"></div>
</div>

<link rel="stylesheet" href="/assets/css/APlayer.min.css">
<script src="/assets/js/APlayer.min.js"></script>
<script src="/assets/js/Meting.min.js"></script>

<script>
const ap = new APlayer({
  container: document.getElementById('aplayer'),
  theme: '#42b983',
  loop: 'all',
  order: 'list',
  preload: 'auto',
  volume: 0.7,
  mutex: true,
  audio: [
    {
      name: '光辉岁月',
      artist: 'Beyond',
      url: '/music/Beyond - 光辉岁月.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '海阔天空',
      artist: 'BEYOND',
      url: '/music/BEYOND - 海阔天空.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: 'Take Me Hand',
      artist: 'DAISHI DANCE,Cécile Corbel',
      url: '/music/DAISHI DANCE,Cécile Corbel - Take Me Hand.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '迷人的危险',
      artist: 'Dance Flow',
      url: '/music/Dance Flow - 迷人的危险.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: 'Sugar',
      artist: 'Maroon 5',
      url: '/music/Maroon 5 - Sugar.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: 'Sugar',
      artist: 'Maroon 5 (2)',
      url: '/music/Maroon 5 - Sugar(2).mp3',
      cover: '/img/avatar.png'
    },
    {
      name: 'Counting Stars',
      artist: 'OneRepublic',
      url: '/music/OneRepublic - Counting Stars.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '有点甜',
      artist: '汪苏泷，BY2',
      url: '/music/汪苏泷，BY2 - 有点甜.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '起风了',
      artist: '买辣椒也用券',
      url: '/music/买辣椒也用券 - 起风了.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '侧脸',
      artist: '于果',
      url: '/music/于果 - 侧脸.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '后来',
      artist: '刘若英',
      url: '/music/刘若英 - 后来.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '十年',
      artist: '陈奕迅',
      url: '/music/十年 - 陈奕迅 (12).mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '告白气球',
      artist: '周杰伦',
      url: '/music/告白气球 - 周杰伦.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '晴天',
      artist: '周杰伦',
      url: '/music/周杰伦 - 晴天.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '简单爱',
      artist: '周杰伦',
      url: '/music/周杰伦 - 简单爱.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '花海',
      artist: '周杰伦',
      url: '/music/周杰伦 - 花海.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '青花瓷',
      artist: '周杰伦',
      url: '/music/周杰伦 - 青花瓷.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '七里香',
      artist: '周杰伦',
      url: '/music/周杰伦 - 七里香.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '兰亭序',
      artist: '周杰伦',
      url: '/music/周杰伦 - 兰亭序.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '夜曲',
      artist: '周杰伦',
      url: '/music/周杰伦 - 夜曲.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '天黑黑',
      artist: '孙燕姿',
      url: '/music/孙燕姿 - 天黑黑.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '开始懂了',
      artist: '孙燕姿',
      url: '/music/孙燕姿 - 开始懂了.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '我怀念的',
      artist: '孙燕姿',
      url: '/music/孙燕姿 - 我怀念的.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '遇见',
      artist: '孙燕姿',
      url: '/music/孙燕姿 - 遇见.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '富士山下',
      artist: '陈奕迅',
      url: '/music/富士山下 - 陈奕迅.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '追光者',
      artist: '岑宁儿',
      url: '/music/岑宁儿 - 追光者.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '可不可以',
      artist: '张紫豪',
      url: '/music/张紫豪 - 可不可以.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '大海',
      artist: '张雨生',
      url: '/music/张雨生 - 大海.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '再见',
      artist: '张震岳',
      url: '/music/张震岳 - 再见.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '隐形的翅膀',
      artist: '张韶涵',
      url: '/music/张韶涵 - 隐形的翅膀.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '山丘',
      artist: '李宗盛',
      url: '/music/李宗盛 - 山丘.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '给自己的歌',
      artist: '李宗盛',
      url: '/music/李宗盛 - 给自己的歌.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '修炼爱情',
      artist: '林俊杰',
      url: '/music/林俊杰 - 修炼爱情.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '江南',
      artist: '林俊杰',
      url: '/music/林俊杰 - 江南.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '一生有你',
      artist: '水木年华',
      url: '/music/水木年华 - 一生有你.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '最后一页',
      artist: '江语晨',
      url: '/music/江语晨 - 最后一页.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '游京',
      artist: 'lucky 小阳 (DJ 版)',
      url: '/music/游京 (DJ 版) - lucky 小阳.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '爱情讯息',
      artist: '郭静',
      url: '/music/爱情讯息 - 郭静.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '猜不透',
      artist: '丁当',
      url: '/music/猜不透 - 丁当.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '稻香',
      artist: '周杰伦',
      url: '/music/稻香 - 周杰伦.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '红豆',
      artist: '王菲',
      url: '/music/红豆 - 王菲.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '明天会更好',
      artist: '群星',
      url: '/music/群星 - 明天会更好.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '荷塘月色',
      artist: '凤凰传奇',
      url: '/music/荷塘月色 - 凤凰传奇.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '这世界那么多人',
      artist: '莫文蔚',
      url: '/music/莫文蔚 - 这世界那么多人.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '日不落',
      artist: '蔡依林',
      url: '/music/蔡依林 - 日不落.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '说爱你',
      artist: '蔡依林',
      url: '/music/蔡依林 - 说爱你.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '红色高跟鞋',
      artist: '蔡健雅',
      url: '/music/蔡健雅 - 红色高跟鞋.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '越来越不懂',
      artist: '蔡健雅',
      url: '/music/蔡健雅 - 越来越不懂.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '演员',
      artist: '薛之谦',
      url: '/music/薛之谦 - 演员.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '春娇与志明',
      artist: '街道办 GDC&欧阳耀莹',
      url: '/music/街道办 GDC&欧阳耀莹 - 春娇与志明.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '素颜',
      artist: '许嵩，何曼婷',
      url: '/music/许嵩，何曼婷 - 素颜.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '南方姑娘',
      artist: '赵雷',
      url: '/music/赵雷 - 南方姑娘.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '成都',
      artist: '赵雷',
      url: '/music/赵雷 - 成都.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '过火',
      artist: '张信哲',
      url: '/music/过火 - 张信哲.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '心墙',
      artist: '郭静',
      url: '/music/郭静 - 心墙.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '因为爱情',
      artist: '陈奕迅',
      url: '/music/陈奕迅 - 因为爱情.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '绿色',
      artist: '陈雪凝',
      url: '/music/陈雪凝 - 绿色.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '青丝',
      artist: '邓寓君 (等什么君) (DJ 版)',
      url: '/music/青丝 (DJ 版)-邓寓君 (等什么君)&DJ Wave.mp3',
      cover: '/img/avatar.png'
    },
    {
      name: '月牙湾',
      artist: '飞儿乐团',
      url: '/music/飞儿乐团 - 月牙湾.mp3',
      cover: '/img/avatar.png'
    }
  ]
});
</script>

<style>
.aplayer-container {
  max-width: 800px;
  margin: 50px auto;
  padding: 20px;
}
.aplayer {
  background: rgba(255, 255, 255, 0.9);
  border-radius: 10px;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.15);
}
</style>
