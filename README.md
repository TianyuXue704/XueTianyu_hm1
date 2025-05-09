# 矩阵运算函数实现思路

## 1. 行列式计算 (`det_matrix`)
- **递归展开法**：
  1. **终止条件**：1x1矩阵直接返回元素值。
  2. **按第一行展开**：遍历第一行元素，生成对应的余子矩阵。
  3. **符号交替**：使用 `sign *= -1` 实现 $(-1)^{i+j}$ 的符号。
  4. **递归计算**：累加 `a[0][j] * det(submat)`。

## 2. 矩阵求逆 (`inv_matrix`)
- **高斯-若当消元法**：
  1. **构造增广矩阵**：原矩阵与单位矩阵拼接为 `n × 2n` 矩阵。
  2. **主元选择**：在列中选取最大绝对值元素，减少数值误差。
  3. **行操作**：
    - **行交换**：将主元行移至当前处理行。
    - **归一化**：主元行除以主元值，使主元变为1。
    - **消元**：用当前行消去其他行的对应列元素。
  4. **提取逆矩阵**：增广矩阵右半部分即为逆矩阵。
- **错误处理**：检查行列式是否为0（奇异矩阵）。

## 3. 矩阵求秩 (`rank_matrix`)
- **高斯消元法**：
  1. **复制矩阵**：避免修改原矩阵数据。
  2. **行阶梯形转换**：
    - **列遍历**：逐列寻找主元（首个非零元素）。
    - **行交换**：将主元行移至当前处理行。
    - **消元**：用当前行消去下方行的对应列元素。
  3. **统计非零行**：秩等于主元数量。
- **阈值处理**：使用 `1e-6` 判断元素是否为0，避免浮点误差。

# 总结
1. **注意点**：
   - 行列式、逆矩阵、迹需验证矩阵为方阵。
   - 逆矩阵需额外检查行列式非零。
2. **整体思路**：
   - 高斯消元中使用主元选择提高精度。
   - 行列式和秩计算处理浮点误差的方法： `1e-6`

# 测试截图
1. **add**：
![add](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/add.png)
2. **sub**：
![sub](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/sub.png)
3. **mul**:
![mul](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/mul.png)
4. **scale**:
![scale](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/scale.png)
5. **transpose**:
![transpose](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/transpose.png)
6. **det**:
![det](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/det.png)
7. **rank**:
![rank](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/rank.png)
8. **inv**:
![inv](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/inv.png)
9. **trace**:
![trace](https://github.com/TianyuXue704/XueTianyu_hm1/blob/main/trace.png)

