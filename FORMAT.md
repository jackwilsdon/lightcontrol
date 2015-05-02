# lightcontrol packet format
A lightcontrol packet consists of 8 bits (1 byte), which is one instruction.

## Fields
| Field      | Offset (bits) | Size (bits) | Description             | Possible Values |
|------------|--------------:|------------:|-------------------------|-----------------|
| **Status** | 7             | 1           | The status for the plug | `0` or `1`      |
| **Group**  | 3             | 2           | The group of the plug   | `0` to `3`      |
| **Plug**   | 1             | 2           | The plug to control     | `0` to `3`      |

## Format
<table>
	<tbody>
		<tr>
			<td align="right"><b>Offset (bits)</b></td>
			<td align="center"><b>7</b></td>
			<td align="center"><b>6</b></td>
			<td align="center"><b>5</b></td>
			<td align="center"><b>4</b></td>
			<td align="center"><b>3</b></td>
			<td align="center"><b>2</b></td>
			<td align="center"><b>1</b></td>
			<td align="center"><b>0</b></td>
		</tr>
		<tr>
			<td align="right"><b>Field</b></td>
			<td align="center"><b>Status</b></td>
			<td align="center" colspan="3"><b>Unused</b></td>
			<td align="center" colspan="2"><b>Group</b></td>
			<td align="center" colspan="2"><b>Plug</b></td>
		</tr>
		<tr>
			<td align="right"><b>Field Bit Values</b></td>
			<td align="center"><b>1</b></td>
			<td colspan="3"></td>
			<td align="center"><b>2</b></td>
			<td align="center"><b>1</b></td>
			<td align="center"><b>2</b></td>
			<td align="center"><b>1</b></td>
		</tr>
	</tbody>
</table>

### Example

<table>
	<tbody>
		<tr>
			<td align="right"><b>Field</b></td>
			<td align="center"><b>Status</b></td>
			<td align="center" colspan="3"><b>Unused</b></td>
			<td align="center" colspan="2"><b>Group</b></td>
			<td align="center" colspan="2"><b>Plug</b></td>
		</tr>
		<tr>
			<td align="right"><b>Binary Data</b></td>
			<td align="center">1</td>
			<td align="center">0</td>
			<td align="center">0</td>
			<td align="center">0</td>
			<td align="center">1</td>
			<td align="center">1</td>
			<td align="center">0</td>
			<td align="center">1</td>
		</tr>
		<tr>
			<td align="right"><b>Values</b>
			<td align="center">On</td>
			<td colspan="3"></td>
			<td align="center" colspan="2">3</td>
			<td align="center" colspan="2">1</td>
		</tr>
	</tbody>
</table>
