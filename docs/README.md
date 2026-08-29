# Media Player Classic - Black Edition (MPC-BE)

## Fork improvements

> This fork includes additional improvements and enhancements on top of the original MPC-BE project.
>
> * **Subtitle layout:** Added Native `Fixed` and `Stack` modes for overlapping subtitles.
> * **Natural sorting:** Added natural file and folder path comparison for playlist sorting.
> * **Unit tests:** Added standalone tests for new components without requiring a full MPC-BE build.
---
### Subtitle Layout

Two subtitle layout modes are available:

* **Native (Fixed):** Uses the original MPC-BE subtitle layout behavior. Each subtitle remains in its assigned position until it disappears; a new subtitle uses the first available position instead of moving existing subtitles.
* **Stack:** New subtitles are added at the bottom and push existing subtitles upward, similar to the subtitle behavior commonly seen on YouTube.

For example, with `A (0–10s)`, `B (8–15s)`, and `C (12–20s)`:

**Fixed**

```text
0–8s     -
         A

8–10s    B
         A

12–15s   B
         C

15–20s   -
         C
```

**Stack**

```text
0–8s     -
         A

8–10s    A
         B

12–15s   B
         C

15–20s   -
         C
```
---
### Natural File and Folder Sorting

Added natural comparison for playlist paths, sorting filenames and folder names according to their **natural text and numeric order** rather than simple lexicographical order.

The comparison supports:

* **Numeric ordering:** Numeric parts are compared by their numeric value, so `2` comes before `10` instead of `10` coming before `2`.
* **Number words:** Written cardinal and ordinal numbers are recognized and ordered by their numeric meaning, so names such as `First`, `Second`, `Third`, `Fifth`, `Tenth`, `Eleven`, and `Twenty-one` are sorted according to their corresponding numbers rather than alphabetically.
* **Leading zeros:** Numbers with leading zeros are compared by their numeric value, so `01` and `1` have the same numeric value while retaining a consistent ordering.
* **Numbers in folder names:** Numeric comparison applies to every path component, including folder names, so numbered folders are sorted naturally together with numbered files.
* **Case-insensitive text:** Alphabetic comparison ignores letter case, so uppercase and lowercase names are sorted together according to their alphabetical order. For example:

  ```text
  A - First.mp4
  A First\test.mp4
  b - Second.mp4
  b Second\test.mp4
  C - Third.mp4
  C Third\test.mp4
  ```
* **Separators and symbols:** Spaces, `-`, `_`, and other non-alphanumeric symbols are treated as separators and do not affect the natural ordering of the surrounding text. For example, `episode 01`, `episode_01`, and `episode-01` are compared naturally, while `Twenty*one` and `Twenty-one` are treated consistently.
* **Mixed text and numbers:** Text and numeric portions are compared independently, producing natural ordering for names containing both descriptive text and episode numbers.

Examples of the resulting natural order:

```text
First.mp4
01 - First.mp4
1 - First.mp4
01 First\test.mp4
1 Episode\test.mp4
Second.mp4
Two.mp4
02 - Second.mp4
2 - Second.mp4
02 Second\test.mp4
2 Episode\test.mp4
Third.mp4
4.mp4
Fifth.mp4
Six.mp4
Seven.mp4
8.mp4
Ninth.mp4
Ten.mp4
10 - Tenth.mp4
10 Tenth\test.mp4
10 Episode\test.mp4
Eleven.mp4
12.mp4
Thirteen.mp4
14.mp4
Fifteen.mp4
16.mp4
Seventeen.mp4
18.mp4
Nineteen.mp4
Twenty.mp4
Twenty*one.mp4
Twenty-one.mp4
21.mp4
22.mp4
Hundred.mp4
```
---

MPC-BE – универсальный проигрыватель аудио и видеофайлов для операционной системы Windows.
Этот проект имеет свою независимую разработку на базе оригинального кода «Media Player Classic» (Gabest) и «Media Player Classic - Home Cinema» (Casimir666).

## Системные требования:
* Процессор с поддержкой SSE2
* Видеокарта с поддержкой DirectX9.0c (PS 3.0)
* Windows 7, 8, 8.1, 10, 11 32-bit/64-bit

---

MPC-BE is a free and open source audio and video player for Windows.
MPC-BE is based on the original Guliverkli project and "Media Player Classic Home Cinema" project, contains additional features and bug fixes.

## System requirements:
* An SSE2 capable CPU
* Video card supporting DirectX9.0c (PS 3.0)
* Windows 7, 8, 8.1, 10, 11 32-bit/64-bit

## Downloads
- [Releases      ](https://github.com/Aleksoid1978/MPC-BE/releases)
- [Nightly Builds](https://github.com/Aleksoid1978/MPC-BE/wiki/Nightly-builds)

## Links
- [Project Page  ](https://sourceforge.net/projects/mpcbe/)
- [Wiki          ](https://github.com/Aleksoid1978/MPC-BE/wiki)
- [Get code      ](https://github.com/Aleksoid1978/MPC-BE.git)

---
 
For the people involved in the development, see Authors.txt.
MPC-BE's code is licensed under GPL v3 (see LICENSE).

Translations are done by various translators (see Authors.txt).

---

MPC-BE makes use of the following 3rd party code:

| Project           | License             | Website                                               |
|-------------------|---------------------|-------------------------------------------------------|
| Bento4            | GPLv2               | https://www.bento4.com/                               |
| CFileVersionInfo  |                     |                                                       |
| CLineNumberEdit   |                     |                                                       |
| compact_enc_det   | Apache-2.0 license  | https://github.com/google/compact_enc_det             |
| coolsb            |                     | https://www.codeproject.com/KB/dialog/coolscroll.aspx |
| CSizingControlBar | GPLv2               | http://datamekanix.com/sizecbar/                      |
| Detours           | MIT License         | https://github.com/microsoft/detours/                 |
| fdk-aac           |                     | https://github.com/mstorsjo/fdk-aac/                  |
| FFmpeg            | GPLv3               | http://ffmpeg.org/                                    |
| dav1d             | BSD License         | https://code.videolan.org/videolan/dav1d/             |
| libdivide         | zlib/Boost License  | https://libdivide.com/                                |
| libflac           | GPLv2/BSD License   | https://github.com/xiph/flac                          |
| libpng            | zlib/libpng License | https://github.com/glennrp/libpng/                    |
| libspeex          | BSD License         | https://speex.org/                                    |
| Little CMS        | MIT License         | https://littlecms.com/                                |
| Logitech SDK      |                     |                                                       |
| MediaInfo         | BSD License         | https://mediaarea.net/MediaInfo                       |
| mfx_dispatch      | MIT License         | https://github.com/Intel-Media-SDK/MediaSDK           |
| RapidJSON         | MIT License         | https://github.com/Tencent/rapidjson                  |
| ResizableLib      | Artistic License    | https://github.com/ppescher/resizablelib              |
| soxr              | LGPL                | https://sourceforge.net/projects/soxr/                |
| TreePropSheet     |                     |                                                       |
| uavs3d            | BSD License         | https://github.com/uavs3/uavs3d                       |
| VirtualDub        | GPLv2               | https://virtualdub.org/                               |
| ZenLib            | zlib License        | https://github.com/MediaArea/ZenLib                   |
| zlib              | zlib License        | https://zlib.net/                                     |
| bs2b              | MIT License         | https://bs2b.sourceforge.net/                         |
| VVdeC             | BSD License         | https://github.com/fraunhoferhhi/vvdec/               |
