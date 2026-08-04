const fs = require("fs");
const path = require("path");

const root = path.resolve(__dirname, "..");
const dataPath = path.join(root, "source", "data", "parts.json");
const outputPath = path.join(root, "source", "parts", "器件用途说明.md");
const parts = JSON.parse(fs.readFileSync(dataPath, "utf8"));

function cell(value) {
  const text = String(value ?? "").trim();
  return (text || "—").replace(/\|/g, "\\|").replace(/\r?\n/g, "<br>");
}

const lifeCategories = [
  "医疗与护理", "健康与营养", "餐饮用品", "文具与办公", "个人护理", "穿戴与户外",
  "宠物用品", "数码配件", "家居与收纳", "纪念与装饰", "休闲娱乐"
];

const rows = parts.map((part, index) =>
  `| ${index + 1} | ${cell(part.model)} | ${cell(part.name)} | ${cell(part.package)} | ${cell(part.category)} | ${cell(part.purpose)} |`
);

const content = [
  "# 器件用途说明",
  "",
  "> 本文档由 `source/data/parts.json` 自动生成，请勿直接编辑；器件资料应在管理页面或 JSON 数据源中修改。",
  "",
  "## 生活用品展开分类",
  "",
  ...lifeCategories.map(category => `- ${category}`),
  "",
  "## 全部器件",
  "",
  "| 序号 | 名称 / 型号 | 补充名称 | 封装 / 规格 | 分类 | 简短用途 |",
  "| ---: | --- | --- | --- | --- | --- |",
  ...rows,
  ""
].join("\n");

const previous = fs.existsSync(outputPath) ? fs.readFileSync(outputPath, "utf8") : "";
if (previous !== content) {
  fs.writeFileSync(outputPath, content, "utf8");
  console.log(`已更新 ${path.relative(root, outputPath)}（${parts.length} 条）`);
} else {
  console.log(`无需更新 ${path.relative(root, outputPath)}（${parts.length} 条）`);
}
