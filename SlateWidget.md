# Slate Widget Overview

**Slate Widget** is Unreal Engine’s low-level UI framework, written entirely in C++. It offers **full control over UI rendering, performance, and customization**, unlike normal `UUserWidget` (UMG), which is higher-level and blueprint-friendly.

## Normal Widget vs. Slate Widget

|-----------------------------------------------------------------------------------------------------|
| Feature        | Normal Widget (UMG) | Slate Widget                                                 |
|----------------|------------------------|-----------------------------------------------------------|
| Language       | Blueprints / C++       | C++ only                                                  |
| Performance    | Slightly heavier       | High-performance, low-level                               |
| Flexibility    | Limited                | Full control over rendering & input                       |
| Use Case       | General UI             | Custom UI elements, editor tools, runtime-critical UI     |
|-----------------------------------------------------------------------------------------------------|

## Why Slate Widget in This Project?

- Needed **high-performance and fully customized UI** for the game.  
- Enables precise control over **fonts, images, buttons, and complex layouts**.  
- Essential for **runtime Slate features** not possible with standard UUserWidget.  

## Rules for Slate Widget

1. **Always store assets in `Content/Slate/…`**  
   - Ensures assets are **cooked and included in packaged builds**.  
   - Using raw file paths (e.g., `ProjectContentDir()`) **breaks Shipping builds**.

2. Fonts, images, and brushes must be referenced via **`/Game/Slate/...` paths** or `FSlateGameResources`.  

3. Slate Widget C++ files must avoid **editor-only code** for Shipping builds.  

**Important:** Following these rules guarantees that your Slate UI works in **Editor, Development, and Production/Shipping builds** reliably.
